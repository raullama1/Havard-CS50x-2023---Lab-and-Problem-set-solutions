-- 6.sql
-- Get the average rating of movies released in the year 2012
SELECT AVG(rating) FROM ratings
JOIN movies ON ratings.movie_id = movies.id
WHERE year = 2012;