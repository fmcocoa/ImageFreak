# -*- coding: utf-8 -*-
import os
from ctypes import (
    CFUNCTYPE,
    cdll,
    c_int,
    c_char_p,
    c_wchar_p
)

_dir = os.path.abspath(os.path.dirname(__file__))

imagefreak = cdll.LoadLibrary(os.path.join(_dir, 'libimagefreak.so'))
CB_FUNC = CFUNCTYPE(None, c_int, c_char_p)


def is_unicode(s):
    try:
        s.decode('ascii')
        return False
    except:
        return True


class PlayerData(object):
    '''Player's game data'''

    def __init__(self, name, avatar, score):
        self.name = name
        self.avatar = avatar
        self.score = score


def composite_fighter(fighter_name, cb):
    _cb = CB_FUNC(cb)
    _fighter_name = c_char_p(fighter_name)
    imagefreak.composite_fighter(_fighter_name, _cb)


def composite_score(player1, player2, dst, lang, cb):
    iswchar = is_unicode(player1.name) or is_unicode(player2.name)

    if cb is not None:
        _cb = CB_FUNC(cb)
    else:
        _cb = None

    output = c_char_p(dst)
    language = c_char_p(lang)

    imagefreak.composite_score(c_wchar_p(player1.name),
                               c_char_p(player1.avatar),
                               c_int(int(player1.score)),
                               c_wchar_p(player2.name),
                               c_char_p(player2.avatar),
                               c_int(int(player2.score)),
                               output,
                               language,
                               iswchar,
                               _cb)


#if __name__ == '__main__':
    #def cb(status, err_msg):
        #pass

    #for i in range(10000):
        #composite_fighter('1', cb)

    #p1 = PlayerData('JOSHEP', '1', 12345678)
    #p2 = PlayerData('VINCENT', '1', 2345678)
    #composite_score(p1, p2, cb)
