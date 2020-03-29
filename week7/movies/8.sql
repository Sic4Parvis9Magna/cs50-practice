SELECT p.name FROM people as p 
JOIN stars as s on s.person_id = p.id
JOIN movies as m on s.movie_id = m.id
WHERE m.title = 'Toy Story';
