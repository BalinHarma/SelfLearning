<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["email"]))
        {
            apologize("You must provide your email address.");
        }
        if (empty($_POST["confirm"]))
        {
            apologize("You must confirm your email address.");
        }
        if ($_POST["email"] != $_POST["confirm"])
        {
            apologize("Your email, and confirmation must match");
        }
        // update users table, with new email address
        query("UPDATE users SET email = ? WHERE id = ?", $_POST["email"], $_SESSION["id"]);

        // redirect to portfolio
        redirect("/");
    }
    else
    {
        // else render form
        render("setmail_form.php", ["title" => "Set email address"]);
    }

?>
