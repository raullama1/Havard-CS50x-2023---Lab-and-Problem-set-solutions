document.addEventListener("DOMContentLoaded", function () {
    const answerChoices = document.querySelectorAll(".answer-choice");
    const feedback = document.querySelectorAll(".feedback");
    const freeResponseInput = document.getElementById("free-response");
    const submitBtn = document.getElementById("submit-btn");

    // Add event listener to each answer choice button
    answerChoices.forEach(function (choice) {
      choice.addEventListener("click", function (event) {
        const selectedButton = event.target;
        const selectedText = selectedButton.textContent.trim();
        const isCorrect = selectedText === "Paris";

        feedback[0].textContent = isCorrect ? "Correct!" : "Incorrect";
        feedback[0].classList.toggle("correct", isCorrect);
        feedback[0].classList.toggle("incorrect", !isCorrect);
      });
    });

    // Add event listener to the submit button
    submitBtn.addEventListener("click", function () {
      const userInput = freeResponseInput.value.trim().toLowerCase();
      const isCorrect = userInput === "leonardo da vinci";

      feedback[1].textContent = isCorrect ? "Correct!" : "Incorrect";
      feedback[1].classList.toggle("correct", isCorrect);
      feedback[1].classList.toggle("incorrect", !isCorrect);
    });
  });
