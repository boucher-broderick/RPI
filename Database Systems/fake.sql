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
   RETURN 'Inputs: '||fromtime::varchar(5)||' '||totime::varchar(5)||' / '||inputstation||' / '||topk::varchar||' / '||w1::varchar||' '||w2::varchar||' '||w3::varchar ;
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

   CREATE TABLE songsplayed AS
   SELECT s.id as songid, s.decade
          , s.energy, s.liveness, s.acousticness
	  , 0.0 as avgrank, count(*) as numtimes
   FROM playedonradio p
        , songs s 
   WHERE s.id = p.songid
         and p.station = inputstation
         and p.playedtime::time >= fromtime
	 and p.playedtime::time <= totime
   GROUP BY s.id, s.decade ;

   UPDATE songsplayed SET avgrank = NULL ;
   
   CREATE TABLE spgenre AS
   SELECT s.genre, count(*) as numtimes
   FROM songsplayed p, song_genre s
   WHERE p.songid = s.songid 
   GROUP BY s.genre ;

   CREATE TABLE scores AS
   SELECT s.songid, sum(sg.numtimes)::float as gs, 0.0 as rs, 0.0 as ss
   FROM song_genre s, spgenre sg
   WHERE s.genre = sg.genre
         and s.songid not in (select songid from songsplayed)
   GROUP BY s.songid ;

   CREATE TABLE bilboardavg as
   SELECT songid, avg(rank) as avgrank FROM bilboard GROUP BY songid ;

   UPDATE songsplayed
   SET avgrank = (select avgrank from bilboardavg b
                  where b.songid = songsplayed.songid)
   WHERE songid in (select songid from bilboardavg) ;

   INSERT INTO scores
   WITH ssbavg AS (select decade, avg(avgrank) as avgrank from songsplayed
                   where decade is not null
		   group by decade)
   SELECT s.id as songid, 0.0 as gs
          , 1.0/abs(b.avgrank - ss.avgrank) as rs, 0.0 as ss
   FROM songs s, bilboardavg b, ssbavg ss
   WHERE s.decade is not null
         and s.id = b.songid
         and s.id not in (select songid from songsplayed)
	 and s.decade = ss.decade ;

   INSERT INTO scores
   WITH ssbavg AS (SELECT avg(energy) as e
                          , avg(liveness) as l
			  , avg(acousticness) as a
		   FROM songsplayed
		   WHERE energy is not null and liveness is not null
		         and acousticness is not null)
   SELECT s.id, 0.0 as gs, 0.0 as rs
          , 1.0/(abs(s.energy-ss.e)+abs(s.liveness-ss.l)+abs(s.acousticness-ss.a)) as ss
   FROM songs s, ssbavg ss
   WHERE s.energy is not null
         and s.liveness is not null
         and s.acousticness is not null
	 and s.id not in (select songid from songsplayed);

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

