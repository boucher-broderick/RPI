SELECT a.id, a.name, COUNT( DISTINCT sc.sid) AS songsonbilboard, MIN(bilboard.rank) AS minboardrank FROM artists AS a --, songsonbillboard, minbillboardrank 
INNER JOIN rollingstonetop500 AS r ON r.artistid = a.id
LEFT JOIN ( SELECT DISTINCT s.id AS sid, s.artistid AS aid 
		  FROM songs AS s
		  INNER JOIN bilboard AS b ON b.songid =s.id
) AS sc ON sc.aid = a.id
LEFT JOIN bilboard ON bilboard.songid = sc.sid
WHERE r.position <21
GROUP BY
 a.id, a.name
ORDER BY a.name ASC ;


