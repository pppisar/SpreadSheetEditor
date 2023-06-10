#include "CInterfaceController.h"

void CInterfaceController::updateTerminalSize() {
    getmaxyx(stdscr, m_terminalHeight, m_terminalWidth);
}

std::string CInterfaceController::readInputString(unsigned startY, unsigned startX, std::string buffer) const {
    unsigned formLen = MIN_WIDTH - startX - 1;
    unsigned bufferStart, bufferEnd = buffer.length();

    unsigned x = startX + buffer.length();
    if (x >= MIN_WIDTH) {
        x = MIN_WIDTH - 1;
        bufferStart = bufferEnd - formLen;
    }
    else
        bufferStart = 0;

    int ch;
    bool isEditing = true;
    curs_set(1);
    while (isEditing) {
        move(startY, startX);
        clrtoeol();
        mvprintw(startY, startX, "%s", buffer.substr(bufferStart, bufferEnd-bufferStart).c_str());
        ch = mvgetch(startY, x);

        switch (ch) {
            case KEY_LEFT:
                if (x > startX)
                    x--;
                else if (x == startX && bufferStart > 0) {
                    bufferStart--;
                    bufferEnd--;
                }
                break;
            case KEY_RIGHT:
                if (x == MIN_WIDTH - 1 && bufferEnd != buffer.length()) {
                    bufferStart++;
                    bufferEnd++;
                }
                else if (x != MIN_WIDTH - 1 && x - startX + bufferStart != buffer.length())
                    x++;
                break;
            case KEY_DC: // Delete key
            case 127:   // Backspace key
            case KEY_BACKSPACE: // Backspace key
                if (x > startX) {
                    if (bufferEnd == buffer.length() && bufferStart != 0) {
                        buffer.erase(x - startX + bufferStart - 1, 1);
                        bufferStart--;
                        bufferEnd--;
                    }
                    else if (bufferEnd != buffer.length()) {
                        buffer.erase(x - startX + bufferStart - 1, 1);
                    }
                    else {
                        buffer.erase(x - startX + bufferStart - 1, 1);
                        bufferEnd--;
                        x--;
                    }
                }
                break;
            case '\n':
            case KEY_ENTER:
                delch();
                isEditing = false;
                break;
            case KEY_UP:
            case KEY_DOWN:
                break;
            default:
                buffer.insert(x - startX + bufferStart, std::string(1, ch));
                if (x == MIN_WIDTH - 1) {
                    bufferStart++;
                    bufferEnd++;
                }
                else {
                    x++;
                    if (bufferEnd - bufferStart != formLen)
                        bufferEnd++;
                }        
                break;
        }
    }
    curs_set(0);

    return buffer;
}

FileName CInterfaceController::getFileName() const {
    std::string fileName;
    FileType type = FileType::Binary;

    move(m_terminalHeight - 2, 0);
    clrtoeol();
    mvprintw(m_terminalHeight - 2, 0, "Enter file name(without extention):");

    move(m_terminalHeight - 1, 0);
    clrtoeol();
    fileName = readInputString(m_terminalHeight - 1, 0, fileName);

    move(m_terminalHeight - 2, 0);
    clrtoeol();
    mvprintw(m_terminalHeight - 2, 0, "Choose file extention: (<- and -> to choose and Enter to aproove)");
    int choosenType = 0;

    move(m_terminalHeight - 1, 0);
    clrtoeol();

    int inpChar;
    while(true) {
        unsigned usedSpace = 0;
        for (int i = 0; i < 2; i++) {
            if (i == choosenType) {
                wattron(stdscr, A_REVERSE);
            }
            mvprintw(m_terminalHeight - 1, usedSpace, "%s", FILETYPE_NAME[i].c_str());
            usedSpace += FILETYPE_NAME[i].length() + 1;
            wattroff(stdscr, A_REVERSE);
        }

        inpChar = getch();

        if (inpChar == KEY_LEFT)
            choosenType = 0;
        else if (inpChar == KEY_RIGHT)
            choosenType = 1;
        else if (inpChar == '\n' || inpChar == KEY_ENTER)
            break;
    }

    switch (choosenType) {
        case 0:
            type = FileType::Binary;
            break;
        case 1:
            type = FileType::Txt;
            break;
        default:
            break;
    }

    renderFooter();

    return std::make_pair(fileName, type);
}