# -*- coding: utf-8 -*-
import shutil
import urlparse

import requests
from flask import Flask, request, jsonify, send_from_directory

from imagefreak import PlayerData, composite_score

app = Flask(__name__)


FB_GRAPH_API = "graph.facebook.com/#?fields=name,picture.width(86).height(86)"


#@app.route('/feed-fighter')
#def feed_fighter():
    #fighter_name = request.args.get('fighter_name', None)

    #if fighter_name is None:
        #return jsonify({'status': False, 'err_msg': 'missing parameter'})

    #return jsonify({'status': True, 'err_msg': None})


@app.route('/gz-feed/battle')
def feed_battle():
    a_name = request.args.get('a_name', None)
    a_pic_name = a_name.encode('ascii', 'xmlcharrefreplace')
    a_pic_link = request.args.get('a_pic', None)
    a_score = request.args.get('a_score', None)

    b_name = request.args.get('b_name', None)
    b_pic_name = b_name.encode('ascii', 'xmlcharrefreplace')
    b_pic_link = request.args.get('b_pic', None)
    b_score = request.args.get('b_score', None)

    if None in (a_name, a_pic_link, a_score, b_name, b_pic_link, b_score):
        return jsonify({'status': False, 'err_msg': 'missing parameters'})

    a_response = requests.get(urlparse.unquote(a_pic_link), stream=True)
    with open('avatars/%s' % a_pic_name, 'wb') as f:
        shutil.copyfileobj(a_response.raw, f);
    del a_response

    b_response = requests.get(urlparse.unquote(b_pic_link), stream=True)
    with open('avatars/%s' % b_pic_name, 'wb') as f:
        shutil.copyfileobj(b_response.raw, f);
    del b_response

    player_a = PlayerData(a_name, a_pic_name, a_score)
    player_b = PlayerData(b_name, b_pic_name, b_score)

    dst = '%s_%s-%s_%s.jpg' % (a_pic_name, a_score, b_pic_name, b_score)
    composite_score(player_a, player_b, dst, None)

    # Get score image
    return send_from_directory(directory='../gz-feed/battle', filename=dst)


if __name__ == '__main__':
    app.run(debug=True)
