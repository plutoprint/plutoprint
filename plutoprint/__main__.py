import plutoprint
import argparse
import re

PAGE_SIZES = {
    'a3': plutoprint.PAGE_SIZE_A3,
    'a4': plutoprint.PAGE_SIZE_A4,
    'a5': plutoprint.PAGE_SIZE_A5,
    'b4': plutoprint.PAGE_SIZE_B4,
    'b5': plutoprint.PAGE_SIZE_B5,
    'letter': plutoprint.PAGE_SIZE_LETTER,
    'legal': plutoprint.PAGE_SIZE_LEGAL,
    'ledger': plutoprint.PAGE_SIZE_LEDGER
}

UNITS_MAP = {
    'pt': plutoprint.UNITS_PT,
    'pc': plutoprint.UNITS_PC,
    'in': plutoprint.UNITS_IN,
    'cm': plutoprint.UNITS_CM,
    'mm': plutoprint.UNITS_MM,
    'px': plutoprint.UNITS_PX
}

METADATA_MAP = {
    'title': plutoprint.PDF_METADATA_TITLE,
    'author': plutoprint.PDF_METADATA_AUTHOR,
    'subject': plutoprint.PDF_METADATA_SUBJECT,
    'keywords': plutoprint.PDF_METADATA_KEYWORDS,
    'creator': plutoprint.PDF_METADATA_CREATOR,
}

def length(value):
    match = re.fullmatch(r'(\d+(?:.\d+)?)(pt|pc|in|cm|mm|px)', value.lower())
    if not match:
        raise argparse.ArgumentTypeError(f"invalid length value: '{value}'")
    num, unit = match.groups()
    return float(num) * UNITS_MAP[unit]

def main():
    parser = argparse.ArgumentParser(prog='plutoprint', description='Convert HTML to PDF.')

    parser.add_argument('input', help='Specify the input HTML filename or URL.')
    parser.add_argument('output', help='Specify the output PDF filename.')

    parser.add_argument('--size', type=str.lower, choices=PAGE_SIZES, help='Specify the page size (eg. A4).')
    parser.add_argument('--margin', type=length, metavar='MARGIN', help='Specify the page margin (eg. 72pt).')
    parser.add_argument('--media', type=str.lower, choices=['print', 'screen'], help='Specify the media type (eg. print, screen).')
    parser.add_argument('--orientation', type=str.lower, choices=['portrait', 'landscape'], help='Specify the page orientation (eg. portrait, landscape).')

    parser.add_argument('--margin-top', type=length, metavar='MARGIN', help='Specify the page margin top (eg. 72pt).')
    parser.add_argument('--margin-right', type=length, metavar='MARGIN', help='Specify the page margin right (eg. 72pt).')
    parser.add_argument('--margin-bottom', type=length, metavar='MARGIN', help='Specify the page margin bottom (eg. 72pt).')
    parser.add_argument('--margin-left', type=length, metavar='MARGIN', help='Specify the page margin left (eg. 72pt).')

    parser.add_argument('--width', type=length, help='Specify the page width (eg. 210mm).')
    parser.add_argument('--height', type=length, help='Specify the page height (eg. 297mm).')

    parser.add_argument('--page-start', type=int, default=plutoprint.MIN_PAGE_COUNT, metavar='START', help='Specify the starting page number to include in the output PDF.')
    parser.add_argument('--page-end', type=int, default=plutoprint.MAX_PAGE_COUNT, metavar='END', help='Specify the ending page number to include in the output PDF.')
    parser.add_argument('--page-step', type=int, default=1, metavar='STEP', help='Specify the step value when iterating through pages.')

    parser.add_argument('--user-style', default=str(), metavar='STYLE', help='Specify the user-defined CSS style to apply to the input document.')
    parser.add_argument('--user-script', default=str(), metavar='SCRIPT', help='Specify the user-defined JavaScript to run after the document has fully loaded.')

    parser.add_argument('--title', help='Set PDF document title.')
    parser.add_argument('--subject', help='Set PDF document subject.')
    parser.add_argument('--author', help='Set PDF document author.')
    parser.add_argument('--keywords', help='Set PDF document keywords.')
    parser.add_argument('--creator', help='Set PDF document creator.')

    parser.add_argument('--version', action='version', version=f'PlutoPrint v{plutoprint.__version__}')

    args = parser.parse_args()

    size = plutoprint.PAGE_SIZE_A4
    if args.size:
        size = PAGE_SIZES[args.size]
    if args.width:
        size = plutoprint.PageSize(args.width, size.height)
    if args.height:
        size = plutoprint.PageSize(size.width, args.height)

    if args.orientation == 'portrait':
        size = size.portrait()
    elif args.orientation == 'landscape':
        size = size.landscape()

    margins = plutoprint.PAGE_MARGINS_NORMAL
    if args.margin:
        margins = plutoprint.PageMargins(args.margin)
    if args.margin_top:
        margins = plutoprint.PageMargins(args.margin_top, margins.right, margins.bottom, margins.left)
    if args.margin_right:
        margins = plutoprint.PageMargins(margins.top, args.margin_right, margins.bottom, margins.left)
    if args.margin_bottom:
        margins = plutoprint.PageMargins(margins.top, margins.right, args.margin_bottom, margins.left)
    if args.margin_left:
        margins = plutoprint.PageMargins(margins.top, margins.right, margins.bottom, args.margin_left)

    media = plutoprint.MEDIA_TYPE_PRINT
    if args.media == 'screen':
        media = plutoprint.MEDIA_TYPE_SCREEN

    book = plutoprint.Book(size, margins, media)
    book.load_url(args.input, args.user_style, args.user_script)

    for name, meta in METADATA_MAP.items():
        value = getattr(args, name)
        if value:
            book.set_metadata(meta, value)

    book.write_to_pdf(args.output, args.page_start, args.page_end, args.page_step)

if __name__ == '__main__':
    main()
