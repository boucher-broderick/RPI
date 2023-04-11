SELECT DISTINCT a.name FROM artists AS a
JOIN songs AS s ON s.artistid = a.id
JOIN bilboard AS b ON s.id = b.songid
WHERE b.weeksonboard > 29
ORDER BY a.name;