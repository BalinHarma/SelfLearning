<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // user error checking....
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol.");
        }
        else if (empty($_POST["stocks"]) || $_POST["stocks"] == 0)
        {
            apologize("You must declare how much stock you want to sell.");
        }
        else if (true != preg_match("/^\d+$/", $_POST["stocks"]))
        {
            apologize("You can only sell a positive and whole number of stocks");
        }
        // if everything is fine
        else
        {
            // capitalize symbol
            $symbol = strtoupper($_POST["symbol"]);
            // make sure user has stocks to sell, aka additional user error checking.....
            $bstocks = query("SELECT * FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $symbol);
            if ($bstocks == false)
            {
                apologize("You do not have shares of that symbol");
            }
            $bstock = $bstocks["0"];
            if ($bstock["stocks"] < $_POST["stocks"])
            {
                apologize("You do not have enough stocks to sell that amount."); 
            }
            // if still fine, delete all stocks, or the appropiate amount
            else if ($bstock["stocks"] == $_POST["stocks"])
            {
                query("DELETE FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $symbol);
            }
            else
            {
                query("UPDATE stocks SET stocks = stocks - ? WHERE id = ? AND symbol = ?", $_POST["stocks"], $_SESSION["id"], $symbol);
            }
            // update users cash
            $stock = lookup($symbol);
            $deposit = $stock["price"] * $_POST["stocks"];
            query("UPDATE users SET cash = cash + ? WHERE id = ?", $deposit, $_SESSION["id"]);
            // update users history
            query("INSERT INTO history (id, symbol, stocks, price, sold) VALUES(?, ?, ?, ?, 1)", 
                        $_SESSION["id"], $symbol,  $_POST["stocks"], $stock["price"]);
            // if user has a mailing address, send receipt email
            $user = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
            if (!empty($user["0"]["email"]))
            {
                mailer("Sold " . $_POST["stocks"] . " shares of " . $symbol . " ( " . $stock["name"] . "), for $" . $deposit . ".", "Sell receipt", $user["0"]["email"]);
            }
            redirect("/");
        }
    }
    else
    {
        // else render form
        render("sell_form.php", ["title" => "Sell"]);
    }
?>
