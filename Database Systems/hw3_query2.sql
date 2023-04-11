SELECT a.name, s.name, MAX(sp.streams) AS max FROM artists AS a
INNER JOIN songs AS s ON s.artistid = a.id
INNER JOIN spotify AS sp ON sp.songid = s.id
INNER JOIN rollingstonetop500 AS r ON r.artistid = a.id
WHERE sp.streams >= 100000 AND r.position < 11
GROUP BY a.name, s.name
ORDER BY a.name ASC, max DESC;