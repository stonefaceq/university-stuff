var slideIndex = 1;
showSlides(slideIndex);
var timeoutID;

function plusSlides(n) {
  showSlides(slideIndex += n);
  clearTimeout(timeoutID);
  timeoutID = setTimeout(function() {
    showSlides(slideIndex += 1);
  }, 4000);
}

function showSlides(n) {
  var i;
  var slides = document.getElementsByClassName("slide");
  if (n > slides.length) {slideIndex = 1}
  if (n < 1) {slideIndex = slides.length}
  for (i = 0; i < slides.length; i++) {
      slides[i].classList.remove("active");
  }
  slides[slideIndex-1].classList.add("active");
  clearTimeout(timeoutID);
  timeoutID = setTimeout(function() {   
    showSlides(slideIndex += 1);
  }, 4000);
}
