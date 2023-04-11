SELECT s.name AS songname, a.name AS artistname, s.decade, (s.duration_ms/(1000*60))::int AS duration
FROM songs s, artists a
WHERE s.artistid = a.id AND (s.duration_ms/(1000*60))::int = (SELECT MIN((duration_ms/(1000*60))::int) FROM songs)
ORDER BY songname, artistname;