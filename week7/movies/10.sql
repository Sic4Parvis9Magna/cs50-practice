SELECT DISTINCT p.name FROM people as p 
JOIN directors as d on d.person_id = p.id
JOIN movies as m on d.movie_id = m.id
JOIN ratings as r on r.movie_id = m.id
WHERE r.rating >= '9.0';