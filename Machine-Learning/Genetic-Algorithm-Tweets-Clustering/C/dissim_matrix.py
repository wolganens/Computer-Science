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
tfidf_vectorizer = TfidfVectorizer()
tfidf_matrix = tfidf_vectorizer.fit_transform(tweets)
d = pairwise_distances(X=tfidf_matrix, Y=None, n_jobs=-1, metric='cosine')    

with open('dissim_matrix.txt', 'w') as f:
	for row in d:
		for column in row:
			f.write(str(column) + ' ')
