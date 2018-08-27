/*
 *  Copyright (c) 2015 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree.
 */

'use strict';

var connection = null;

var peerConnectionConfig = {
  'iceServers': [
    {'urls': 'stun:stun.stunprotocol.org:3478'},
    {'urls': 'stun:stun.l.google.com:19302'},
  ]
};


var startButton = document.getElementById('start_source_button');
var stopButton = document.getElementById('stop_source_button');
var callButton = document.getElementById('peer_connect');
var hangupButton = document.getElementById('disconnect_all');

startButton.onclick = start;
callButton.onclick = call;
hangupButton.onclick = hangup;
stopButton.onclick = stop_local_stream;

var video1 = document.querySelector('video#video1');
var video2 = document.querySelector('video#video2');

var pc1Local;
var pc1Remote;
var offerOptions = {
  offerToReceiveAudio: 1,
  offerToReceiveVideo: 1
};

function gotStream(stream) {
  trace('Received local stream');
  video1.srcObject = stream;
  window.localStream = stream;
}

function stop_local_stream()
{
  video1.srcObject = null;
  window.localStream = null;
  hangup();
}

function start() {
  trace('Requesting local stream');
  navigator.mediaDevices.getUserMedia({
    audio: true,
    video: true
  })
  .then(gotStream)
  .catch(function(e) {
    console.log('getUserMedia() error: ', e);
  });
}

function call() {
  trace('Starting calls');
  var audioTracks = window.localStream.getAudioTracks();
  var videoTracks = window.localStream.getVideoTracks();
  if (audioTracks.length > 0) {
    trace('Using audio device: ' + audioTracks[0].label);
  }
  if (videoTracks.length > 0) {
    trace('Using video device: ' + videoTracks[0].label);
  }
  // Create an RTCPeerConnection via the polyfill.
  var servers = peerConnectionConfig;
  pc1Local = new RTCPeerConnection(servers);
  pc1Remote = new RTCPeerConnection(servers);
  pc1Remote.ontrack = gotRemoteStream1;
  pc1Local.onicecandidate = iceCallback1Local;
  pc1Remote.onicecandidate = iceCallback1Remote;
  trace('pc1: created local and remote peer connection objects');

  window.localStream.getTracks().forEach(
    function(track) {
      pc1Local.addTrack(
        track,
        window.localStream
      );
    }
  );
  trace('Adding local stream to pc1Local');
  pc1Local.createOffer(
    offerOptions
  ).then(
    gotDescription1Local,
    onCreateSessionDescriptionError
  );
}

function onCreateSessionDescriptionError(error) {
  trace('Failed to create session description: ' + error.toString());
}

function gotDescription1Local(desc) {
  pc1Local.setLocalDescription(desc);
  trace('Offer from pc1Local \n' + desc.sdp);
  pc1Remote.setRemoteDescription(desc);
  // Since the 'remote' side has no media stream we need
  // to pass in the right constraints in order for it to
  // accept the incoming offer of audio and video.
  pc1Remote.createAnswer().then(
    gotDescription1Remote,
    onCreateSessionDescriptionError
  );
}

function gotDescription1Remote(desc) {
  pc1Remote.setLocalDescription(desc);
  trace('Answer from pc1Remote \n' + desc.sdp);
  pc1Local.setRemoteDescription(desc);
}


function hangup() {
  trace('Ending calls');
  pc1Local.close();
  pc1Remote.close();
  pc1Local = pc1Remote = null;
}

function gotRemoteStream1(e) {
  if (video2.srcObject !== e.streams[0]) {
    video2.srcObject = e.streams[0];
    trace('pc1: received remote stream');
  }
}

function iceCallback1Local(event) {
  handleCandidate(event.candidate, pc1Remote, 'pc1: ', 'local');
}

function iceCallback1Remote(event) {
  handleCandidate(event.candidate, pc1Local, 'pc1: ', 'remote');
}

function handleCandidate(candidate, dest, prefix, type) {
  dest.addIceCandidate(candidate)
  .then(
    onAddIceCandidateSuccess,
    onAddIceCandidateError
  );
  trace(prefix + 'New ' + type + ' ICE candidate: ' +
      (candidate ? candidate.candidate : '(null)'));
}

function onAddIceCandidateSuccess() {
  trace('AddIceCandidate success.');
}

function onAddIceCandidateError(error) {
  trace('Failed to add ICE candidate: ' + error.toString());
}