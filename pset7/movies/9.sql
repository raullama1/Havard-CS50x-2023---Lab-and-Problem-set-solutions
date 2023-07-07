-- 9.sql
-- Get the names of people who have starred in movies released in the year 2004, ordered by their birth year
SELECT name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.year = 2004
ORDER BY people.birth;