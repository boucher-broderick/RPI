SELECT station, count(DISTINCT songid) AS numsongs
from  playedonradio p
WHERE  station LIKE 'm%'  AND songid IN (
	SELECT p2.songid
    FROM playedonradio p2
    GROUP BY p2.songid
	HAVING count(DISTINCT p2.station)<=2)
GROUP BY station
ORDER BY  station;