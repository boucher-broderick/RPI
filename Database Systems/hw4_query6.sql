SELECT s.name AS songname, a.name AS artistname, to_char(sum(sp.streams), '999,999,999,999') totalstreams
FROM songs s, artists a, spotify sp
WHERE s.artistid = a.id AND s.id = sp.songid
GROUP BY s.id, s.name, a.id, a.name HAVING sum(sp.streams) >= ALL (
	SELECT 0.5*sum(streams) 
	FROM spotify 
	GROUP BY songid
)
ORDER BY songname, artistname;
