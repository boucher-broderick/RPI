DROP FUNCTION IF EXISTS recommendation(time,time,varchar,int,float,float,float);
DROP FUNCTION IF EXISTS recommendation_helper(time,time,varchar,int,float,float,float);

DROP TABLE IF EXISTS songsimilarity;

CREATE TABLE songsimilarity(
    songid       int
    , songname   text
    , artistname text
    , songscore  float
) ;    

CREATE OR REPLACE FUNCTION
    recommendation_helper(fromtime time
               , totime time
               , inputstation varchar
               , topk int
	       , w1 float, w2 float, w3 float) RETURNS VARCHAR AS $$
BEGIN

END ;
$$ LANGUAGE plpgsql ;

CREATE OR REPLACE FUNCTION
    recommendation(fromtime time
               , totime time
               , inputstation varchar
               , topk int
	       , w1 float, w2 float, w3 float)
    RETURNS SETOF songsimilarity AS $$
DECLARE
   myrow songsimilarity%rowtype ;
BEGIN



-------------------------------------------

CREATE TABLE songsplayed AS
   SELECT s.id as songid, s.decade
          , s.energy, s.liveness, s.acousticness
	  , 0.0 as avgrank, count(*) as numtimes
   FROM songs s 
   JOIN (
      SELECT songid
      FROM playedonradio
      WHERE station = inputstation
         and playedtime::time >= fromtime
	 and playedtime::time <= totime
   ) p ON s.id = p.songid
   GROUP BY s.id, s.decade ;

   UPDATE songsplayed SET avgrank = NULL ;
   
   
   
-------------------------------------------

  CREATE TABLE spgenre AS
   SELECT s.genre, count(*) as numtimes
   FROM songsplayed p
   JOIN (
      SELECT songid, genre
      FROM song_genre
   ) s ON p.songid = s.songid
   GROUP BY s.genre ;
   

-------------------------------------------

   CREATE TABLE scores AS
   SELECT s.songid, sum(sg.numtimes)::float as gs, 0.0 as rs, 0.0 as ss
   FROM song_genre s
   JOIN spgenre sg ON s.genre = sg.genre
   LEFT JOIN songsplayed p ON s.songid = p.songid
   WHERE p.songid IS NULL
   GROUP BY s.songid ;
   
   
   
-------------------------------------------
   CREATE TABLE bilboardavg as
   SELECT songid, avg(rank) as avgrank FROM bilboard GROUP BY songid ;

   UPDATE songsplayed
   SET avgrank = (select avgrank from bilboardavg b
                  where b.songid = songsplayed.songid)
   WHERE EXISTS ( select 1 songid from bilboardavg) ;


----------------------------------------------------


WITH ssbavg AS (
    SELECT decade, AVG(avgrank) AS avgrank 
    FROM songsplayed
    WHERE decade IS NOT NULL
    GROUP BY decade
)
INSERT INTO scores(songid, gs, rs, ss)
SELECT s.id AS songid, 0.0 AS gs, 1.0/ABS(b.avgrank - ss.avgrank) AS rs, 0.0 AS ss
FROM songs AS s
INNER JOIN bilboardavg AS b ON s.id = b.songid
INNER JOIN ssbavg AS ss ON s.decade = ss.decade
WHERE s.decade IS NOT NULL
AND s.id NOT IN (SELECT songid FROM songsplayed);



-------------------------------------------

INSERT INTO scores (songid, gs, rs, ss)
SELECT s.id, 0.0 as gs, 0.0 as rs,
       1.0/(abs(s.energy-ss.e)+abs(s.liveness-ss.l)+abs(s.acousticness-ss.a)) as ss
FROM songs s
CROSS JOIN (SELECT avg(energy) as e, avg(liveness) as l, avg(acousticness) as a
            FROM songsplayed
            WHERE energy is not null and liveness is not null and acousticness is not null) ss
WHERE s.energy is not null
  AND s.liveness is not null
  AND s.acousticness is not null
  AND s.id NOT IN (SELECT songid FROM songsplayed);



-------------------------------------------

    FOR myrow IN SELECT s.id as songid
                       , s.name as songname
		       , a.name as artistname
		       , w1*sum(sc.gs) + w2*sum(sc.rs) + w3*sum(sc.ss) as songscore
         FROM songs s, artists a, scores sc
         WHERE s.artistid = a.id and sc.songid = s.id
	 GROUP BY s.id, s.name, a.name
	 ORDER BY songscore DESC, songname ASC
	 LIMIT topk
   LOOP
       RETURN NEXT myrow ;
   END LOOP ;

   DROP TABLE bilboardavg;
   DROP TABLE scores;
   DROP TABLE spgenre ;
   DROP TABLE songsplayed ;
   
   RETURN ;
END ;
$$ LANGUAGE plpgsql ;
