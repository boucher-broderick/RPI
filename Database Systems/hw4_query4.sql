SELECT a.name AS artistname, COUNT(DISTINCT por.songid) AS numsongs, MIN(FOO.minpos) AS bestpos
FROM public.artists AS a
INNER JOIN public.songs AS s ON a.id = s.artistid
LEFT JOIN public.playedonradio AS por ON s.id = por.songid
INNER JOIN (
	SELECT rst1.artistid, MIN(rst1.position) AS minpos
	FROM public.rollingstonetop500 AS rst1
	GROUP BY  rst1.artistid HAVING MIN(rst1.position) <= 20
) AS FOO ON a.id = FOO.artistid
INNER JOIN public.rollingstonetop500 AS rst ON a.id = rst.artistid
WHERE rst.position >=20
GROUP BY a.name
ORDER BY numsongs DESC, bestpos DESC, artistname ASC;