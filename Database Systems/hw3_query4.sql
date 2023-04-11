SELECT DISTINCT s.id AS songid, s.name AS songname, a.name AS artistname FROM songs AS s
INNER JOIN artists AS a ON s.artistid = a.id
INNER JOIN spotify AS sp ON sp.songid = s.id
WHERE DATE_PART('dow', sp.streamdate) IN (0, 6) 
  AND s.id NOT IN (
    SELECT songid FROM spotify
    WHERE DATE_PART('dow', streamdate) IN (1, 4)
  )
ORDER BY s.name ASC, a.name ASC;