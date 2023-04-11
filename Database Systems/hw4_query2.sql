SELECT s.name AS songname, a.name AS artistname, COUNT(por.songid) AS numplayed
FROM songs AS s
INNER JOIN artists AS a ON s.artistid = a.id
LEFT JOIN playedonradio AS por ON s.id = por.songid
INNER JOIN (SELECT DISTINCT b.songid 
		   FROM PUBLIC.bilboard as b WHERE b.rank BETWEEN 6 AND 50
		   )  AS FOO ON s.id = FOO.songid
WHERE s.loudness <= -11.5 
GROUP BY s.name, a.name
ORDER BY numplayed DESC, songname, artistname ASC;


--(
--	SELECT DISTINCT por1.songid, COUNT(por1.songid) AS numplayed 
--	FROM public.playedonradio as por1
--	GROUP BY  por1.songid
--)