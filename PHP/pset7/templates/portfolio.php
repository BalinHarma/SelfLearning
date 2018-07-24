<div class="menu">
    <a href="logout.php">Log Out</a> #
    <a href="quote.php">quote</a> #
    <a href="sell.php">sell</a> #
    <a href="buy.php">buy</a> #
    <a href="history.php">history</a> #
    <a href="setmail.php">Set email address</a>
</div>
<table>

    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
    </thead>

    <tbody>
    <?php

        foreach ($positions as $position)
        {
            print("<tr>");
            print("<td>" . $position["symbol"] . "</td>");
            print("<td>" . $position["name"] . "</td>");
            print("<td>" . $position["shares"] . "</td>");
            print("<td>$" . number_format($position["price"], 2, ',', ' ') . "</td>");
            print("<td>$" . number_format($position["total"], 2, ',', ' ') . "</td>");
            print("</tr>");
        }

    ?>
        <tr>
            <td colspan="4">CASH</td>
            <td>$<?=(number_format($wallet, 2, ',', ' ')) ?></td>
        </tr>
    </tbody>

</table>
