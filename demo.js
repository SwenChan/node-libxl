var xl = require('./lib/libxl');

function fillSheet(sheet) {
    var book = sheet.book,
        row = 1,
        format;

    sheet
        .writeString(row, 0, 'Some string')
        .writeString(row, 0, 'Unicode - فارسی - Қазақша');
    row++;

    format = book.addFormat();
    sheet
        .writeString(row, 0, 'green', format);
    sheet.cellFormat(row, 0)
        .setFillPattern(xl.FILLPATTERN_SOLID)
        .setPatternForegroundColor(xl.COLOR_GREEN);
}

function fillBook(book) {
    var sheet = book.addSheet('Sheet 1');

    fillSheet(sheet);
}

var xlsBook =  new xl.Book(xl.BOOK_TYPE_XLS),
    xlsxBook = new xl.Book(xl.BOOK_TYPE_XLSX);

fillBook(xlsBook);
fillBook(xlsxBook);

xlsBook.writeSync('demo.xls');
xlsxBook.writeSync('demo.xlsx');