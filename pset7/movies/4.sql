-- 4.sql
-- Get the count of movies that have a rating of 10
SELECT COUNT(title) FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE rating = 10;