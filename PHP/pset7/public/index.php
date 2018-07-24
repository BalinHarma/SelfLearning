<?php

    // configuration
    require("../includes/config.php"); 

    // render portfolio
    $positions = [];
    $rows = query("SELECT * FROM stocks WHERE id = ?", $_SESSION["id"]);
    $wallets = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
    $wallet = $wallets[0];
    //settype($wallet["cash"], "double");
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["stocks"],
                "symbol" => $row["symbol"],
                "total" => $row["stocks"] * $stock["price"]
            ];
        }
    }
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "wallet" => $wallet["cash"]]);

?>
