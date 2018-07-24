<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol.");
        }
        else
        {
            $stock = lookup($_POST["symbol"]);
            if($stock === false)
            {
                apologize("could not found stock.");
            }
            else
            {
                render("query_result.php", $stock);
            }
        }
    }
    else
    {
        // else render form
        render("lookup_form.php", ["title" => "Quote"]);
    }
?>
