<div>
    <img alt="Under Construction" src="/img/construction.gif"/>
</div>
<div>
    <a href="logout.php">Log Out</a> or
    <a href="quote.php">quote</a>
</div>
<div>
    A share of <?= htmlspecialchars($name) ?>, (<?= htmlspecialchars($symbol) ?>) costs $<?= htmlspecialchars(number_format($price, 2, ',', ' ')) ?>.
</div>
