<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // looking for user errors...
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol.");
        }
        else if (empty($_POST["stocks"]) || $_POST["stocks"] == 0)
        {
            apologize("You must declare how much stock you want to buy.");
        }
        else if (true != preg_match("/^\d+$/", $_POST["stocks"]))
        {
            apologize("You can only buy a positive and whole number of stocks");
        }
        else
        {
            // looking for stock
            $stock = lookup($_POST["symbol"]);
            if ($stock === false)
            {
                apologize("Could not found symbol");
            }
            // capitalizing tock symbol
            $symbol = strtoupper($_POST["symbol"]);
            // calculatin price, and looking up user cash
            $price = $stock["price"] * $_POST["stocks"];
            $wallet = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
            $balance = $wallet["0"];
            // if not enough money, tell them off
            if ($balance["cash"] < $price)
            {
                apologize("You do not have enough money to buy that amount."); 
            }
            // else update stock table, with recent purchase
            else
            {
                query("INSERT INTO stocks (id, symbol, stocks) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE stocks = stocks + ?", 
                        $_SESSION["id"], $symbol, $_POST["stocks"], $_POST["stocks"]);
            }
            // update users cash
            query("UPDATE users SET cash = cash - ? WHERE id = ?", $price, $_SESSION["id"]);
            // update users hisory
            query("INSERT INTO history (id, symbol, stocks, price) VALUES(?, ?, ?, ?)", 
                        $_SESSION["id"], $symbol, $_POST["stocks"], $stock["price"]);
            // if user povided an address, send receipt email
            if (!empty($balance["email"]))
            {
                mailer("Bought " . $_POST["stocks"] . " shares of " . $symbol . " ( " . $stock["name"] . "), for $" . $price . ".", "Buy receipt", $balance["email"]);
            }
            redirect("/");
        }
    }
    else
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
    }
?>
