from flask import Flask, render_template, request
app = Flask(__name__)
count = 0

@app.route('/')
def hello_world():
    global count
    count += 1
    return render_template('index.html', c=count)

if __name__ == '__main__':

    app.run()