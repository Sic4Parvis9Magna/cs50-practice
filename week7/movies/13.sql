SELECT DISTINCT(p.name) FROM (SELECT  m.id as mv_id FROM people as p 
JOIN stars as s on s.person_id = p.id
JOIN movies as m on s.movie_id = m.id
WHERE p.name = 'Kevin Bacon' AND p.birth = '1958') as kb
JOIN movies as m on kb.mv_id = m.id
JOIN stars as s ON s.movie_id = kb.mv_id
JOIN people as p ON p.id = s.person_id
WHERE p.name <> 'Kevin Bacon';