SELECT s.name AS songname, a.name AS artistname, MIN(b.rank) AS minrank
FROM songs AS s
INNER JOIN artists AS a ON s.artistid = a.id
INNER JOIN (
	SELECT DISTINCT b1.songid 
	FROM bilboard AS b1
	WHERE b1.weeksonboard >= 30
) AS FOO ON FOO.songid = s.id
LEFT JOIN bilboard AS b ON s.id = b.songid
LEFT JOIN spotify AS sp ON s.id = sp.songid
WHERE sp.songid IS NULL AND b.songid IS NOT NULL
GROUP BY s.name, a.name
ORDER BY minrank, songname, artistname ASC;