const char* prefContent = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width">
  <title>Survey Form</title>
  <link href="style.css" rel="stylesheet" type="text/css" />
  <style>
    .fixed-header {
        position: fixed;
        top: 0;
        left: 0;
        padding: 10px 20px;
        background: linear-gradient(to right, hsl(230, 97%, 62%), hsl(69, 97%, 62%)); /* Gradient background */
        -webkit-background-clip: text;
        background-clip: text;
        color: transparent; /* Makes the text take the color of the background */
        -webkit-text-fill-color: transparent; /* For WebKit browsers */
        z-index: 1000; /* Ensures the header stays above other content */
        letter-spacing: 3px;
        text-transform: uppercase;
        font-size: 40px;
        font-weight: 900;
        transition: background .3s;
    }

    /* DEFAULTS */
    /* =============================================== */
    body {
      display: grid;
      place-content: center;
      /*background: linear-gradient(to top, hsl(230, 97%, 62%), white);*/
      background-attachment: fixed;
      min-height: 100vh;
      margin: 0;
      padding: 40px;
      box-sizing: border-box;

      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, 'Open Sans', sans-serif;
    }


    /* MAIN */
    /* =============================================== */
    .rad-label {
      display: flex;
      align-items: center;

      border-radius: 100px;
      padding: 14px 16px;
      margin: 10px 0;

      cursor: pointer;
      transition: .3s;
    }

    .rad-label:hover,
    .rad-label:focus-within {
      background: hsla(0, 0%, 80%, .14);
    }

    .rad-input {
      position: absolute;
      left: 0;
      top: 0;
      width: 1px;
      height: 1px;
      opacity: 0;
      z-index: -1;
    }

    .rad-design {
      width: 22px;
      height: 22px;
      border-radius: 100px;

      background: linear-gradient(to right bottom, hsl(230, 97%, 62%), hsl(69, 97%, 62%));
      position: relative;
    }

    .rad-design::before {
      content: '';

      display: inline-block;
      width: inherit;
      height: inherit;
      border-radius: inherit;

      background: hsl(0, 0%, 90%);
      transform: scale(1.1);
      transition: .3s;
    }

    .rad-input:checked+.rad-design::before {
      transform: scale(0);
    }

    .rad-text {
      color: hsl(0, 0%, 60%);
      margin-left: 14px;
      letter-spacing: 3px;
      text-transform: uppercase;
      font-size: 16px;
      font-weight: 900;

      transition: .3s;
    }

    .rad-input:checked~.rad-text {
      color: hsl(0, 0%, 40%);
    }


    /* ABS */
    /* ====================================================== */
    .abs-site-link {
      position: fixed;
      bottom: 40px;
      left: 20px;
      color: hsla(0, 0%, 0%, .5);
      font-size: 16px;
    }

    .question-heading {
        font-family: 'Open Sans', sans-serif; /* Same as the submit button */
        font-size: 24px; /* Keeping the size as specified */
        color: #506EEC; /* Same color as the rad-text class */
        margin-bottom: 10px; /* Spacing below the heading */
        text-transform: uppercase; /* As per rad-text class */
        font-weight: 900; /* As per rad-text class */
        letter-spacing: 3px; /* As per rad-text class */
    }

    .submit-button {
      background: linear-gradient(to right bottom, hsl(230, 97%, 62%), hsl(69, 97%, 62%));
        border: none;
        padding: 10px 20px;
        border-radius: 5px;
        color: white;
      transition: background .3s;
    }

    .submit-button:hover {
        background-color: #405DCB; /* Darker shade for hover effect */
    }
  </style>
</head>
<body>
  <div class="fixed-header">
     Fill in <br> your <br> preferences!
  </div>
  <!-- Survey Form -->
  <form id="surveyForm">
    <!-- Age Range Question -->
    <div>
      <p class="question-heading">Age Range:</p>
        <label class="rad-label">
            <input type="radio" class="rad-input" id="age1" name="age" value="18-24">
            <div class="rad-design"></div>
            <div class="rad-text">18-24</div>
        </label>

        <label class="rad-label">
            <input type="radio" class="rad-input" id="age2" name="age" value="25-34">
            <div class="rad-design"></div>
            <div class="rad-text">25-34</div>
        </label>

        <label class="rad-label">
            <input type="radio" class="rad-input" id="age3" name="age" value="35-44">
            <div class="rad-design"></div>
            <div class="rad-text">35-44</div>
        </label>

        <label class="rad-label">
            <input type="radio" class="rad-input" id="age4" name="age" value="45-55">
            <div class="rad-design"></div>
            <div class="rad-text">45-55</div>
        </label>

        <label class="rad-label">
            <input type="radio" class="rad-input" id="age5" name="age" value="55+">
            <div class="rad-design"></div>
            <div class="rad-text">55+</div>
        </label>
    </div>

    <div>
      <p class="question-heading">Gender:</p>
        <label class="rad-label">
            <input type="radio" class="rad-input" id="gender1" name="gender" value="Male">
            <div class="rad-design"></div>
            <div class="rad-text">Male</div>
        </label>

        <label class="rad-label">
            <input type="radio" class="rad-input" id="gender2" name="gender" value="Female">
            <div class="rad-design"></div>
            <div class="rad-text">Female</div>
        </label>

        <label class="rad-label">
            <input type="radio" class="rad-input" id="gender3" name="gender" value="Non-binary">
            <div class="rad-design"></div>
            <div class="rad-text">Non-binary</div>
        </label>

        <label class="rad-label">
            <input type="radio" class="rad-input" id="gender4" name="gender" value="Prefer not to say">
            <div class="rad-design"></div>
            <div class="rad-text">Prefer not to say</div>
        </label>
    </div>

    <div>
        <p class="question-heading">Relationship type:</p>
        <label class="rad-label">
            <input type="radio" class="rad-input" id="option1" name="preference" value="Romantic">
            <div class="rad-design"></div>
            <div class="rad-text">Romantic</div>
        </label>

        <label class="rad-label">
            <input type="radio" class="rad-input" id="option2" name="preference" value="Platonic">
            <div class="rad-design"></div>
            <div class="rad-text">Platonic</div>
        </label>

        <label class="rad-label">
            <input type="radio" class="rad-input" id="option3" name="preference" value="Open to All">
            <div class="rad-design"></div>
            <div class="rad-text">Open to All</div>
        </label>
    </div>


    <!-- Interests/Hobbies Question -->
    <p class="question-heading">Interests/Hobbies (choose 5):</p>
    <input type="checkbox" id="hobby1" name="hobby" value="Sports">
    <label for="hobby1" class="rad-text">Sports</label><br>
    <input type="checkbox" id="hobby1" name="hobby" value="Sports">
    <label for="hobby1" class="rad-text">Sports</label><br>

    <input type="checkbox" id="hobby2" name="hobby" value="Fashion">
    <label for="hobby2" class="rad-text">Fashion</label><br>

    <input type="checkbox" id="hobby3" name="hobby" value="Gaming">
    <label for="hobby3" class="rad-text">Gaming</label><br>

    <input type="checkbox" id="hobby4" name="hobby" value="Food">
    <label for="hobby4" class="rad-text">Food</label><br>

    <input type="checkbox" id="hobby5" name="hobby" value="Cooking">
    <label for="hobby5" class="rad-text">Cooking</label><br>

    <input type="checkbox" id="hobby6" name="hobby" value="Animals">
    <label for="hobby6" class="rad-text">Animals</label><br>

    <input type="checkbox" id="hobby7" name="hobby" value="Comedy">
    <label for="hobby7" class="rad-text">Comedy</label><br>

    <input type="checkbox" id="hobby8" name="hobby" value="Fitness">
    <label for="hobby8" class="rad-text">Fitness</label><br>

    <input type="checkbox" id="hobby9" name="hobby" value="Books">
    <label for="hobby9" class="rad-text">Books</label><br>

    <input type="checkbox" id="hobby10" name="hobby" value="Film">
    <label for="hobby10" class="rad-text">Film</label><br>

    <input type="checkbox" id="hobby11" name="hobby" value="Music">
    <label for="hobby11" class="rad-text">Music</label><br>

    <input type="checkbox" id="hobby12" name="hobby" value="Sustainability">
    <label for="hobby12" class="rad-text">Sustainability</label><br>

    <input type="checkbox" id="hobby13" name="hobby" value="LGBTQ+">
    <label for="hobby13" class="rad-text">LGBTQ+</label><br>

    <input type="checkbox" id="hobby14" name="hobby" value="Photography">
    <label for="hobby14" class="rad-text">Photography</label><br>

    <input type="checkbox" id="hobby15" name="hobby" value="Technology">
    <label for="hobby15" class="rad-text">Technology</label><br>

    <input type="checkbox" id="hobby16" name="hobby" value="News">
    <label for="hobby16" class="rad-text">News</label><br>

    <input type="checkbox" id="hobby17" name="hobby" value="Politics">
    <label for="hobby17" class="rad-text">Politics</label><br>

    <input type="checkbox" id="hobby18" name="hobby" value="Travel">
    <label for="hobby18" class="rad-text">Travel</label><br>

    <input type="checkbox" id="hobby19" name="hobby" value="Outdoors">
    <label for="hobby19" class="rad-text">Outdoors</label><br>

    <input type="submit" value="Submit" class="submit-button rad-text" style="margin-top: 20px;">
  </form>


  <!-- Placeholder for displaying responses -->
  <div id="responseDisplay" class="rad-text" style="margin-top: 20px;"></div>

  <script>
    document.getElementById('surveyForm').addEventListener('submit', function(event) {
      event.preventDefault(); // Prevent the default form submission

      var response = '';

      // Handling Age Range
      var ageElements = document.getElementsByName('age');
      for (var i = 0; i < ageElements.length; i++) {
        if (ageElements[i].checked) {
          pref += ageElements[i].value + '\n ';
          break;
        }
      }

      // Handling Gender
      var genderElements = document.getElementsByName('gender');
      for (var i = 0; i < genderElements.length; i++) {
        if (genderElements[i].checked) {
          pref += genderElements[i].value + '\n ';
          break;
        }
      }
      // Handling Interests/Hobbies
          var hobbiesResponse = [];
          var hobbyElements = document.getElementsByName('hobby');
          for (var i = 0; i < hobbyElements.length; i++) {
            if (hobbyElements[i].checked) {
              hobbiesResponse.push(hobbyElements[i].value);
            }
          }
          if (hobbiesResponse.length > 0) {
            pref += hobbiesResponse.join('\n') + '\n ';
          }


          document.getElementById('responseDisplay').innerText = "Submitted successfully!";
          window.location.href = 'profile.html'; //adjust
        });
      </script>
  </form>
</body>
</html>
)rawliteral";
