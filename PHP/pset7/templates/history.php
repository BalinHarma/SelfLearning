<div class="menu">
    <a href="logout.php">Log Out</a> #
    <a href="quote.php">quote</a> #
    <a href="sell.php">sell</a> #
    <a href="buy.php">buy</a> #
    <a href="/">portfolio</a> #
    <a href="setmail.php">Set email address</a>
</div>
<table>

    <thead>
        <tr>
            <th>Action</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Total</th>
            <th>Date</th>
        </tr>
    </thead>

    <tbody>
    <?php

        foreach ($histories as $history)
        {
            print("<tr>");
            switch ($history["action"]) {
                case 0: print("<td>Bought</td>");
                    break;
                case 1: print("<td>Sold</td>");
            }
            print("<td>" . $history["symbol"] . "</td>");
            print("<td>" . $history["stocks"] . "</td>");
            print("<td>$" . $history["price"] . "</td>");
            print("<td>$" . number_format($history["total"], 2, ',', ' ') . "</td>");
            print("<td>" . $history["date"] . "</td>");
            print("</tr>");
        }

    ?>

    </tbody>

</table>
