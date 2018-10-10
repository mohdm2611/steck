const accountSid = 'AC66dead53c973552acb3620dce467cdb9';
const authToken = 'c45a57ff20582c121a6bd1a2f2df7673';
const client = require('twilio')(accountSid, authToken);

client.calls
  .create({
    url: 'https://handler.twilio.com/twiml/EH1df2828d59176b7dc35e85e9d9cd9cdf?Name=Jane',
    to: '+918686427332',
    from: '+15312081934',
  })
  .then(call => process.stdout.write(call.sid));