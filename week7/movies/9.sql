SELECT dist.name FROM (SELECT DISTINCT p.id, p.name as name FROM people as p 
JOIN stars as s on s.person_id = p.id
JOIN movies as m on s.movie_id = m.id
WHERE m.year = 2004
ORDER BY case when p.birth = NULL then 1 else 0 end, p.birth DESC) as dist;