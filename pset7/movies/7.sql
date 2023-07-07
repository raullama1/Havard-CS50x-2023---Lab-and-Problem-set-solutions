-- 7.sql
-- Get the titles and ratings of movies from the year 2010, ordered by rating in descending order and then by title
SELECT movies.title, ratings.rating FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE year = 2010
ORDER BY rating DESC, title;

