<?php

    // configuration
    require("../includes/config.php"); 

    // render history
    $histories = [];
    $rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
    foreach ($rows as $row)
    {
        $histories[] = [
            "price" => $row["price"],
            "stocks" => $row["stocks"],
            "symbol" => $row["symbol"],
            "date" => $row["date"],
            "action" => $row["sold"],
            "total" => $row["price"] * $row["stocks"]
        ];
    }
    render("history.php", ["title" => "History", "histories" => $histories]);

?>
