SELECT DISTINCT a.name AS artistname 
FROM artists a     
INNER JOIN rollingstonetop500 r ON r.artistid = a.id 
WHERE(
	SELECT MIN(EXTRACT(YEAR FROM b.chartdate))      
	FROM bilboard b      
	INNER JOIN songs s ON b.songid = s.id      
	WHERE s.artistid = a.id AND b.rank < 11
) > 2004 
ORDER BY artistname;