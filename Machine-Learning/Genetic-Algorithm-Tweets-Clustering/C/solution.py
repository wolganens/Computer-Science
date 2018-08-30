from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import pairwise_distances
from nltk.corpus import stopwords
import json
import re

def load_tweets():
    """
    Carrega os tweets do arquivo Tweets.json
    :return: lista de objetos
    """
    try:
        with open('../Tweets.json', 'r') as f:
            file_text = f.read()
            tweets = json.loads(file_text)
            return tweets
    except Exception as e:
        print("Falha ao abrir arquivo json")
        raise e

def remove_stop_words(tweets):
    """
    Remove palavras que não acrescentam informação, adicionalmente remove pontuação
    :param tweets: lista com os tweets
    :return:
    """
    for t in tweets:
        t['text'] = " ".join([re.sub(r'[\.\?\!\,]', '', word.lower()) for word in t['text'].split() if not word in stopwords.words('english')])
    return tweets


tweets = [t['text'] for t in remove_stop_words(load_tweets())]

with open('solution.txt', 'r') as f:
	data = [[int(n) for n in line.split()] for line in f]
	n = len(data)
	m = len(data[0])
	for v in range(m):
		v_tweets_index = [i for i in range(n) if data[i][v] == 1]
		v_tweets = [tweets[i] for i in v_tweets_index]
		with open('{}.txt'.format(v), 'w') as f:
			f.write('\n'.join(v_tweets))
			f.write('\n')