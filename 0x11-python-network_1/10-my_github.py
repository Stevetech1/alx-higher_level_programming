#!/usr/bin/python3
"""
My github!
takes my Github credentials (username and password)
and uses the Github API to display my id
"""

import requests
from sys import argv
from requests.auth import HTTPBasicAuth


if __name__ == "__main__":
    url = 'https://api.github.com/user'
    req = requests.get(url, auth=HTTPBasicAuth(argv[1], argv[2]))
    if (req.status_code == 200):
        req_json = req.json()
        print(req_json['id'])
    else:
        print("None")
