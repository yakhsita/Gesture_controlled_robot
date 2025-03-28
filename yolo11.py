import cv2
from ultralytics import YOLO

# Load the YOLO model
model = YOLO("yolo11n.pt")  # Ensure you have the correct model file

# Open the webcam (0 is the default webcam)
cap = cv2.VideoCapture(0)

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    # Run YOLO detection on the frame
    results = model(frame)

    # Plot the results on the frame
    annotated_frame = results[0].plot()

    # Display the frame with detections
    cv2.imshow("YOLO11 Real-Time Detection", annotated_frame)

    # Press 'q' to exit
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

# Release resources
cap.release()
cv2.destroyAllWindows()
