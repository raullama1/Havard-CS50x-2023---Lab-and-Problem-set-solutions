-- 5.sql
-- Get the titles and years of movies that start with "Harry Potter", ordered by year
SELECT title, year FROM movies
WHERE title LIKE "Harry Potter%"
ORDER BY year;