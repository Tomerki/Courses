$(function () {
    $('form').submit(async e => {
        e.preventDefault();
        
        const q = $('#search').val();
        
        var r = await fetch('/ClientRates/Index?query=' + q);
        var d = await r.json();

        const template = $('#template').html();
        let results = '';
        for (var item in d) {
            let row = template;
            for (var key in d[item]) {
                row = row.replaceAll('{' + key + '}', d[item][key]);
                row = row.replaceAll('%7B' + key + '%7D', d[item][key]);

            } results += row;
        }

        $('tbody').html(results);
    });
})