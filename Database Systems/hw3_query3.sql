SELECT DISTINCT s.id, s.name, a.name FROM songs AS s
INNER JOIN artists AS a ON s.artistid = a.id
LEFT JOIN bilboard AS b ON b.songid = s.id 
	AND b.chartdate >= '2020-03-01' 
	AND b.chartdate <= '2020-05-31' 
	AND b.weeksonboard >= 5
LEFT JOIN (
    SELECT pr.songid, COUNT(*) AS played
    FROM playedonradio AS pr
    WHERE pr.playedtime >= '2020-05-01' AND pr.playedtime <= '2020-05-31'
    GROUP BY songid
) r ON r.songid = s.id
WHERE (b.rank IS NOT NULL OR r.played >= 20)
ORDER BY s.name ASC, a.name ASC;