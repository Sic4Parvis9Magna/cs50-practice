SELECT m.title FROM people as p 
JOIN stars as s on s.person_id = p.id
JOIN movies as m on s.movie_id = m.id
JOIN ratings as r on r.movie_id = m.id
WHERE p.name = 'Chadwick Boseman' 
ORDER BY r.rating DESC
LIMIT 5;