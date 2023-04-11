SELECT DISTINCT sg.genre FROM song_genre AS sg
INNER JOIN songs AS s ON sg.songid = s.id
INNER JOIN bilboard AS b ON s.id = b.songid
WHERE b.rank >3  AND sg.genre NOT IN (
	SELECT DISTINCT sg1.genre FROM song_genre AS sg1
	INNER JOIN songs AS s1 ON sg1.songid = s1.id
	INNER JOIN bilboard AS b1 ON s1.id = b1.songid
	WHERE b1.rank < 4)

GROUP BY sg.genre
HAVING COUNT(DISTINCT b.songid) >2
ORDER BY sg.genre ASC;