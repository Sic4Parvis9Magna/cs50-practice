SELECT AVG(r.rating) FROM movies AS m
JOIN ratings as r on r.movie_id = m.id
WHERE m.year = 2012;