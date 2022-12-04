from flask import Flask, render_template, Response, request
import cv2
# from flask_serial import Serial
import time
import serial 

app = Flask(__name__)

camera = cv2.VideoCapture(1)

# for i in range(10):
#     # Reading all bytes available bytes till EOL  
#     line = ser.read() 
#     print('line', line)
#     if line:
#         # Converting Byte Strings into unicode strings
#         string = line.decode()  
#         # Converting Unicode String into integer
#         num = int(string) 
#         print(num)
 
# ser.close()

locked = False


def gen_frames():  
    while True:
        success, frame = camera.read()  # read the camera frame
        if not success:
            break
        else:
            ret, buffer = cv2.imencode('.jpg', frame)
            frame = buffer.tobytes()
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n') 


@app.route('/', methods=['POST', 'GET'])
def index():
    global locked
    rung = False # TODO: Change this to the button from the circuit 
    # locked = False # TODO: Change this to modify from code
    # print(ser.read())

    # print(doorbell_status())

    if request.method == 'GET':
        pass
    if request.method == 'POST':
        form_data = request.form
        display_text = form_data['display'] # send to display
        door_control = form_data['door_status'] # send to circuit
        
        if door_control == 'lock':
            locked = True
        else:
            locked = False

        
        print(door_control, display_text)

    return render_template('index.html', rung=rung, locked=locked)

def doorbell():
    ser = serial.Serial('COM5', 9600)
    try:
        ser.open()
    except serial.SerialException as e:
         yield 'event:error\n' + 'data:' + 'Serial port error({0}): {1}\n\n'.format(e.errno, e.strerror)
         messageid = messageid + 1
    str_list = []

    while True:
        time.sleep(0.01)
        nextchar = ser.read()
        if nextchar:
            str_list.append(nextchar)
            print(str_list[-1])
        else:
            if len(str_list) > 0:
                yield 'id:' + str(messageid) + '\n' + 'data:' + ''.join(str_list) + '\n\n'
                messageid = messageid + 1
                str_list = []

@app.route('/video_feed')
def video_feed():
    return Response(gen_frames(), mimetype='multipart/x-mixed-replace; boundary=frame')

# @app.route('/test')
# def test():
#     newresponse = Response(doorbell(), mimetype="text/event-stream")
#     newresponse.headers.add('Access-Control-Allow-Origin', '*')
#     newresponse.headers.add('Cache-Control', 'no-cache')
#     return test

if __name__ == "__main__":
    app.run(debug=True, threaded=True)
