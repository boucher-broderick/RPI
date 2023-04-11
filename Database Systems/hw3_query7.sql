SELECT DISTINCT a.id, a.name
FROM artists AS a
INNER JOIN rollingstonetop500 AS r ON a.id = r.artistid
INNER JOIN songs AS s ON a.id = s.artistid
INNER JOIN playedonradio AS p ON s.id = p.songid
WHERE p.playedtime BETWEEN '2020-05-01 00:00:00'::timestamp AND '2020-07-31 23:59:59'::timestamp
GROUP BY a.id, a.name
HAVING COUNT(DISTINCT p.station) >= 3 AND COUNT(*) >= 5
ORDER BY a.id ASC;
