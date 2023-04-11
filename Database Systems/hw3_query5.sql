SELECT DISTINCT s.id AS songid, s.name AS songname, a.name AS artistname
FROM songs AS s
INNER JOIN artists AS a ON s.artistid = a.id
INNER JOIN playedonradio AS r ON r.songid = s.id
INNER JOIN spotify AS sp ON sp.songid = s.id
LEFT JOIN bilboard AS b ON b.songid = s.id
WHERE sp.streams >= 1000000
  AND b.songid IS NULL
ORDER BY songname ASC, artistname ASC;