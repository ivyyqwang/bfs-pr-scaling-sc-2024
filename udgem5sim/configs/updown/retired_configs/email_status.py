# Based on https://docs.python.org/3/library/email.examples.html, https://levelup.gitconnected.com/an-alternative-way-to-send-emails-in-python-5630a7efbe84
# modules
import smtplib
from email.message import EmailMessage
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from email.mime.application import MIMEApplication
import smtplib
import ssl
smtp_server = "smtp.gmail.com" # for Gmail
port = 587  # For starttls

sender_email = 'upstream.notifications@gmail.com'  # email address used to generate password
receiver_email = 'andronicus@uchicago.edu' # a list of recipients 
password = 'ezpmdwojifkmtdnf' # the 16 code generated

def send_status_mail(suffix,exit_code):   
    msg = MIMEMultipart()
    msg["Subject"] = "Upstream Notification:" + str(suffix)
    msg["From"] = sender_email
    msg['To'] = receiver_email
    text = str(suffix) + " run done with exit code :" + str(exit_code)
    body_text = MIMEText(text, 'plain')  # 
    msg.attach(body_text)  # attaching the text body into msg
    context = ssl.create_default_context()
    # Try to log in to server and send email
    try:
        server = smtplib.SMTP(smtp_server, port)
        server.ehlo()  # check connection
        server.starttls(context=context)  # Secure the connection
        server.ehlo()  # check connection
        server.login(sender_email, password)

        # Send email here
        server.sendmail(sender_email, receiver_email, msg.as_string())

    except Exception as e:
        # Print any error messages to stdout
        print(e)
    finally:
        server.quit()
