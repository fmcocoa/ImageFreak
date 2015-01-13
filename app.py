# -*- coding: utf-8 -*-
import requests
from flask import Flask, request, jsonify

app = Flask(__name__)


FB_GRAPH_API = "graph.facebook.com/#?fields=name,picture.width(86).height(86)"


@app.route('/feed-fighter', methods=['POST'])
def feed_fighter():
    fighter_name = request.form.get('fighter_name', None)

    if fighter_name is None:
        return jsonify({'status': False, 'err_msg': 'missing parameter'})

    return jsonify({'status': True, 'err_msg': None})


@app.route('/feed-score', methods=['POST'])
def feed_score():
    uid1 = request.form.get('uid1', None)
    score1 = reuquest.form.get('score1', 0)

    uid2 = request.form.get('uid2', None)
    score2 = reuquest.form.get('score2', 0)

    if uid1 is None or score1 == 0 \
            or uid2 is None or score2 == 0:
        return jsonify({'status': False, 'err_msg': 'missing parameters'})

    # Grab player names and avatars from facebook
    try:
        r1 = requests.get(FB_GRAPH_API.replace('#', uid1)).json()
        r2 = requests.get(FB_GRAPH_API.replace('#', uid2)).json()

        uname1 = r1['name']
        pic1 = r1['picture']['url']

        uname2 = r2'name']
        pic2 = r2['picture']['url']
    except:
        return jsonify({'status': False,
                        'err_msg': 'failed to grab user info from facebook'})

    # Get score image

    return jsonify({'status': True, 'err_msg': None})


if __name__ == '__main__':
    app.run()
