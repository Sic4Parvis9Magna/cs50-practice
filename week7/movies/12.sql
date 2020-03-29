SELECT m.title FROM (SELECT  m.id as mv_id FROM people as p 
JOIN stars as s on s.person_id = p.id
JOIN movies as m on s.movie_id = m.id
WHERE p.name = 'Helena Bonham Carter') as hm
JOIN movies as m on hm.mv_id = m.id
JOIN stars as s ON s.movie_id = hm.mv_id
JOIN people as p ON p.id = s.person_id
WHERE p.name = 'Johnny Depp';