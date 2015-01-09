# -*- coding: utf-8 -*-
from ctypes import (
    CFUNCTYPE,
    cdll,
    c_int,
    c_char_p,
    c_wchar_p
)

imagefreak = cdll.LoadLibrary('libimagefreak.so')
CB_FUNC = CFUNCTYPE(None, c_int, c_char_p)


def is_unicode(s):
    if isinstance(s, unicode):
        return True
    else:
        return False


class PlayerData(object):
    def __init__(self, name, avatar, score):
        self.name = name
        self.avatar = avatar
        self.score = score

def composite_fighter(fighter_name, cb):
    _cb = CB_FUNC(cb)
    _fighter_name = c_char_p(fighter_name)
    imagefreak.composite_fighter(_fighter_name, _cb)


def composite_score(player1, player2, cb):
    iswchar = is_unicode(player1.name) or is_unicode(player2.name)
    _cb = CB_FUNC(cb)
    output = c_char_p('xxx')

    imagefreak.composite_score(c_wchar_p(player1.name),
                               c_char_p(player1.avatar),
                               c_int(123456789),
                               c_wchar_p(player2.name),
                               c_char_p(player2.avatar),
                               c_int(23456789),
                               output,
                               iswchar,
                               _cb)


if __name__ == '__main__':
    def cb(status, err_msg):
        print 'Status: ', status

    #composite_fighter('1', cb)

    p1 = PlayerData('JOSHEP', '1', 12345678)
    p2 = PlayerData('VINCENT', '1', 2345678)
    composite_score(p1, p2, cb)
