from flask import Flask, request
from flask_cors import CORS
from joblib import load

clf = load('model.joblib') 

app = Flask(__name__)
CORS(app)

@app.route('/', methods=['GET'])
def Home():
    return "<p> Hello :) !!</p>"


@app.route('/Predict', methods=['GET', 'POST'])
def Predict():
    global predicted
    if request.method == 'POST':
        requested_data = request.get_json()
        data = []
        data.append(requested_data)
        predicted = clf.predict(data)
        return str(predicted.tolist()[0]) , 200
    else:
        return str(predicted.tolist()[0]) , 200
    

if __name__ == "main":
    app.run(host="localhost", debug=True)